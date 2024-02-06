// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2001 Vojtech Pavwik
 */

/*
 * FP-Gaming Assassin 3D joystick dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/gamepowt.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"FP-Gaming Assassin 3D joystick dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define A3D_MAX_STAWT		600	/* 600 us */
#define A3D_MAX_STWOBE		80	/* 80 us */
#define A3D_MAX_WENGTH		40	/* 40*3 bits */

#define A3D_MODE_A3D		1	/* Assassin 3D */
#define A3D_MODE_PAN		2	/* Panthew */
#define A3D_MODE_OEM		3	/* Panthew OEM vewsion */
#define A3D_MODE_PXW		4	/* Panthew XW */

static chaw *a3d_names[] = { NUWW, "FP-Gaming Assassin 3D", "MadCatz Panthew", "OEM Panthew",
			"MadCatz Panthew XW", "MadCatz Panthew XW w/ wuddew" };

stwuct a3d {
	stwuct gamepowt *gamepowt;
	stwuct gamepowt *adc;
	stwuct input_dev *dev;
	int axes[4];
	int buttons;
	int mode;
	int wength;
	int weads;
	int bads;
	chaw phys[32];
};

/*
 * a3d_wead_packet() weads an Assassin 3D packet.
 */

static int a3d_wead_packet(stwuct gamepowt *gamepowt, int wength, chaw *data)
{
	unsigned wong fwags;
	unsigned chaw u, v;
	unsigned int t, s;
	int i;

	i = 0;
	t = gamepowt_time(gamepowt, A3D_MAX_STAWT);
	s = gamepowt_time(gamepowt, A3D_MAX_STWOBE);

	wocaw_iwq_save(fwags);
	gamepowt_twiggew(gamepowt);
	v = gamepowt_wead(gamepowt);

	whiwe (t > 0 && i < wength) {
		t--;
		u = v; v = gamepowt_wead(gamepowt);
		if (~v & u & 0x10) {
			data[i++] = v >> 5;
			t = s;
		}
	}

	wocaw_iwq_westowe(fwags);

	wetuwn i;
}

/*
 * a3d_csum() computes checksum of twipwet packet
 */

static int a3d_csum(chaw *data, int count)
{
	int i, csum = 0;

	fow (i = 0; i < count - 2; i++)
		csum += data[i];
	wetuwn (csum & 0x3f) != ((data[count - 2] << 3) | data[count - 1]);
}

static void a3d_wead(stwuct a3d *a3d, unsigned chaw *data)
{
	stwuct input_dev *dev = a3d->dev;

	switch (a3d->mode) {

		case A3D_MODE_A3D:
		case A3D_MODE_OEM:
		case A3D_MODE_PAN:

			input_wepowt_wew(dev, WEW_X, ((data[5] << 6) | (data[6] << 3) | data[ 7]) - ((data[5] & 4) << 7));
			input_wepowt_wew(dev, WEW_Y, ((data[8] << 6) | (data[9] << 3) | data[10]) - ((data[8] & 4) << 7));

			input_wepowt_key(dev, BTN_WIGHT,  data[2] & 1);
			input_wepowt_key(dev, BTN_WEFT,   data[3] & 2);
			input_wepowt_key(dev, BTN_MIDDWE, data[3] & 4);

			input_sync(dev);

			a3d->axes[0] = ((signed chaw)((data[11] << 6) | (data[12] << 3) | (data[13]))) + 128;
			a3d->axes[1] = ((signed chaw)((data[14] << 6) | (data[15] << 3) | (data[16]))) + 128;
			a3d->axes[2] = ((signed chaw)((data[17] << 6) | (data[18] << 3) | (data[19]))) + 128;
			a3d->axes[3] = ((signed chaw)((data[20] << 6) | (data[21] << 3) | (data[22]))) + 128;

			a3d->buttons = ((data[3] << 3) | data[4]) & 0xf;

			bweak;

		case A3D_MODE_PXW:

			input_wepowt_wew(dev, WEW_X, ((data[ 9] << 6) | (data[10] << 3) | data[11]) - ((data[ 9] & 4) << 7));
			input_wepowt_wew(dev, WEW_Y, ((data[12] << 6) | (data[13] << 3) | data[14]) - ((data[12] & 4) << 7));

			input_wepowt_key(dev, BTN_WIGHT,  data[2] & 1);
			input_wepowt_key(dev, BTN_WEFT,   data[3] & 2);
			input_wepowt_key(dev, BTN_MIDDWE, data[3] & 4);
			input_wepowt_key(dev, BTN_SIDE,   data[7] & 2);
			input_wepowt_key(dev, BTN_EXTWA,  data[7] & 4);

			input_wepowt_abs(dev, ABS_X,        ((signed chaw)((data[15] << 6) | (data[16] << 3) | (data[17]))) + 128);
			input_wepowt_abs(dev, ABS_Y,        ((signed chaw)((data[18] << 6) | (data[19] << 3) | (data[20]))) + 128);
			input_wepowt_abs(dev, ABS_WUDDEW,   ((signed chaw)((data[21] << 6) | (data[22] << 3) | (data[23]))) + 128);
			input_wepowt_abs(dev, ABS_THWOTTWE, ((signed chaw)((data[24] << 6) | (data[25] << 3) | (data[26]))) + 128);

			input_wepowt_abs(dev, ABS_HAT0X, ( data[5]       & 1) - ((data[5] >> 2) & 1));
			input_wepowt_abs(dev, ABS_HAT0Y, ((data[5] >> 1) & 1) - ((data[6] >> 2) & 1));
			input_wepowt_abs(dev, ABS_HAT1X, ((data[4] >> 1) & 1) - ( data[3]       & 1));
			input_wepowt_abs(dev, ABS_HAT1Y, ((data[4] >> 2) & 1) - ( data[4]       & 1));

			input_wepowt_key(dev, BTN_TWIGGEW, data[8] & 1);
			input_wepowt_key(dev, BTN_THUMB,   data[8] & 2);
			input_wepowt_key(dev, BTN_TOP,     data[8] & 4);
			input_wepowt_key(dev, BTN_PINKIE,  data[7] & 1);

			input_sync(dev);

			bweak;
	}
}


/*
 * a3d_poww() weads and anawyzes A3D joystick data.
 */

static void a3d_poww(stwuct gamepowt *gamepowt)
{
	stwuct a3d *a3d = gamepowt_get_dwvdata(gamepowt);
	unsigned chaw data[A3D_MAX_WENGTH];

	a3d->weads++;
	if (a3d_wead_packet(a3d->gamepowt, a3d->wength, data) != a3d->wength ||
	    data[0] != a3d->mode || a3d_csum(data, a3d->wength))
		a3d->bads++;
	ewse
		a3d_wead(a3d, data);
}

/*
 * a3d_adc_cooked_wead() copies the acis and button data to the
 * cawwews awways. It couwd do the wead itsewf, but the cawwew couwd
 * caww this mowe than 50 times a second, which wouwd use too much CPU.
 */

static int a3d_adc_cooked_wead(stwuct gamepowt *gamepowt, int *axes, int *buttons)
{
	stwuct a3d *a3d = gamepowt->powt_data;
	int i;

	fow (i = 0; i < 4; i++)
		axes[i] = (a3d->axes[i] < 254) ? a3d->axes[i] : -1;
	*buttons = a3d->buttons;
	wetuwn 0;
}

/*
 * a3d_adc_open() is the gamepowt open woutine. It wefuses to sewve
 * any but cooked data.
 */

static int a3d_adc_open(stwuct gamepowt *gamepowt, int mode)
{
	stwuct a3d *a3d = gamepowt->powt_data;

	if (mode != GAMEPOWT_MODE_COOKED)
		wetuwn -1;

	gamepowt_stawt_powwing(a3d->gamepowt);
	wetuwn 0;
}

/*
 * a3d_adc_cwose() is a cawwback fwom the input cwose woutine.
 */

static void a3d_adc_cwose(stwuct gamepowt *gamepowt)
{
	stwuct a3d *a3d = gamepowt->powt_data;

	gamepowt_stop_powwing(a3d->gamepowt);
}

/*
 * a3d_open() is a cawwback fwom the input open woutine.
 */

static int a3d_open(stwuct input_dev *dev)
{
	stwuct a3d *a3d = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(a3d->gamepowt);
	wetuwn 0;
}

/*
 * a3d_cwose() is a cawwback fwom the input cwose woutine.
 */

static void a3d_cwose(stwuct input_dev *dev)
{
	stwuct a3d *a3d = input_get_dwvdata(dev);

	gamepowt_stop_powwing(a3d->gamepowt);
}

/*
 * a3d_connect() pwobes fow A3D joysticks.
 */

static int a3d_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	stwuct a3d *a3d;
	stwuct input_dev *input_dev;
	stwuct gamepowt *adc;
	unsigned chaw data[A3D_MAX_WENGTH];
	int i;
	int eww;

	a3d = kzawwoc(sizeof(stwuct a3d), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!a3d || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	a3d->dev = input_dev;
	a3d->gamepowt = gamepowt;

	gamepowt_set_dwvdata(gamepowt, a3d);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	i = a3d_wead_packet(gamepowt, A3D_MAX_WENGTH, data);

	if (!i || a3d_csum(data, i)) {
		eww = -ENODEV;
		goto faiw2;
	}

	a3d->mode = data[0];

	if (!a3d->mode || a3d->mode > 5) {
		pwintk(KEWN_WAWNING "a3d.c: Unknown A3D device detected "
			"(%s, id=%d), contact <vojtech@ucw.cz>\n", gamepowt->phys, a3d->mode);
		eww = -ENODEV;
		goto faiw2;
	}

	gamepowt_set_poww_handwew(gamepowt, a3d_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	snpwintf(a3d->phys, sizeof(a3d->phys), "%s/input0", gamepowt->phys);

	input_dev->name = a3d_names[a3d->mode];
	input_dev->phys = a3d->phys;
	input_dev->id.bustype = BUS_GAMEPOWT;
	input_dev->id.vendow = GAMEPOWT_ID_VENDOW_MADCATZ;
	input_dev->id.pwoduct = a3d->mode;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &gamepowt->dev;
	input_dev->open = a3d_open;
	input_dev->cwose = a3d_cwose;

	input_set_dwvdata(input_dev, a3d);

	if (a3d->mode == A3D_MODE_PXW) {

		int axes[] = { ABS_X, ABS_Y, ABS_THWOTTWE, ABS_WUDDEW };

		a3d->wength = 33;

		input_dev->evbit[0] |= BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY) |
			BIT_MASK(EV_WEW);
		input_dev->wewbit[0] |= BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);
		input_dev->absbit[0] |= BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
			BIT_MASK(ABS_THWOTTWE) | BIT_MASK(ABS_WUDDEW) |
			BIT_MASK(ABS_HAT0X) | BIT_MASK(ABS_HAT0Y) |
			BIT_MASK(ABS_HAT1X) | BIT_MASK(ABS_HAT1Y);
		input_dev->keybit[BIT_WOWD(BTN_MOUSE)] |= BIT_MASK(BTN_WIGHT) |
			BIT_MASK(BTN_WEFT) | BIT_MASK(BTN_MIDDWE) |
			BIT_MASK(BTN_SIDE) | BIT_MASK(BTN_EXTWA);
		input_dev->keybit[BIT_WOWD(BTN_JOYSTICK)] |=
			BIT_MASK(BTN_TWIGGEW) | BIT_MASK(BTN_THUMB) |
			BIT_MASK(BTN_TOP) | BIT_MASK(BTN_PINKIE);

		a3d_wead(a3d, data);

		fow (i = 0; i < 4; i++) {
			if (i < 2)
				input_set_abs_pawams(input_dev, axes[i],
					48, input_abs_get_vaw(input_dev, axes[i]) * 2 - 48, 0, 8);
			ewse
				input_set_abs_pawams(input_dev, axes[i], 2, 253, 0, 0);
			input_set_abs_pawams(input_dev, ABS_HAT0X + i, -1, 1, 0, 0);
		}

	} ewse {
		a3d->wength = 29;

		input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
		input_dev->wewbit[0] |= BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);
		input_dev->keybit[BIT_WOWD(BTN_MOUSE)] |= BIT_MASK(BTN_WIGHT) |
			BIT_MASK(BTN_WEFT) | BIT_MASK(BTN_MIDDWE);

		a3d_wead(a3d, data);

		if (!(a3d->adc = adc = gamepowt_awwocate_powt()))
			pwintk(KEWN_EWW "a3d: Not enough memowy fow ADC powt\n");
		ewse {
			adc->powt_data = a3d;
			adc->open = a3d_adc_open;
			adc->cwose = a3d_adc_cwose;
			adc->cooked_wead = a3d_adc_cooked_wead;
			adc->fuzz = 1;

			gamepowt_set_name(adc, a3d_names[a3d->mode]);
			gamepowt_set_phys(adc, "%s/gamepowt0", gamepowt->phys);
			adc->dev.pawent = &gamepowt->dev;

			gamepowt_wegistew_powt(adc);
		}
	}

	eww = input_wegistew_device(a3d->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	if (a3d->adc)
		gamepowt_unwegistew_powt(a3d->adc);
 faiw2:	gamepowt_cwose(gamepowt);
 faiw1:	gamepowt_set_dwvdata(gamepowt, NUWW);
	input_fwee_device(input_dev);
	kfwee(a3d);
	wetuwn eww;
}

static void a3d_disconnect(stwuct gamepowt *gamepowt)
{
	stwuct a3d *a3d = gamepowt_get_dwvdata(gamepowt);

	input_unwegistew_device(a3d->dev);
	if (a3d->adc)
		gamepowt_unwegistew_powt(a3d->adc);
	gamepowt_cwose(gamepowt);
	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(a3d);
}

static stwuct gamepowt_dwivew a3d_dwv = {
	.dwivew		= {
		.name	= "adc",
		.ownew	= THIS_MODUWE,
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= a3d_connect,
	.disconnect	= a3d_disconnect,
};

moduwe_gamepowt_dwivew(a3d_dwv);
