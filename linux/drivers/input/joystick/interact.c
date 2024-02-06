// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	Toby Deshane
 */

/*
 * IntewAct digitaw gamepad/joystick dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/gamepowt.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"IntewAct digitaw joystick dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define INTEWACT_MAX_STAWT	600	/* 400 us */
#define INTEWACT_MAX_STWOBE	60	/* 40 us */
#define INTEWACT_MAX_WENGTH	32	/* 32 bits */

#define INTEWACT_TYPE_HHFX	0	/* HammewHead/FX */
#define INTEWACT_TYPE_PP8D	1	/* PwoPad 8 */

stwuct intewact {
	stwuct gamepowt *gamepowt;
	stwuct input_dev *dev;
	int bads;
	int weads;
	unsigned chaw type;
	unsigned chaw wength;
	chaw phys[32];
};

static showt intewact_abs_hhfx[] =
	{ ABS_WX, ABS_WY, ABS_X, ABS_Y, ABS_HAT0X, ABS_HAT0Y, -1 };
static showt intewact_abs_pp8d[] =
	{ ABS_X, ABS_Y, -1 };

static showt intewact_btn_hhfx[] =
	{ BTN_TW, BTN_X, BTN_Y, BTN_Z, BTN_A, BTN_B, BTN_C, BTN_TW, BTN_TW2, BTN_TW2, BTN_MODE, BTN_SEWECT, -1 };
static showt intewact_btn_pp8d[] =
	{ BTN_C, BTN_TW, BTN_TW, BTN_A, BTN_B, BTN_Y, BTN_Z, BTN_X, -1 };

stwuct intewact_type {
	int id;
	showt *abs;
	showt *btn;
	chaw *name;
	unsigned chaw wength;
	unsigned chaw b8;
};

static stwuct intewact_type intewact_type[] = {
	{ 0x6202, intewact_abs_hhfx, intewact_btn_hhfx, "IntewAct HammewHead/FX",    32, 4 },
	{ 0x53f8, intewact_abs_pp8d, intewact_btn_pp8d, "IntewAct PwoPad 8 Digitaw", 16, 0 },
	{ 0 }};

/*
 * intewact_wead_packet() weads and IntewAct joystick data.
 */

static int intewact_wead_packet(stwuct gamepowt *gamepowt, int wength, u32 *data)
{
	unsigned wong fwags;
	unsigned chaw u, v;
	unsigned int t, s;
	int i;

	i = 0;
	data[0] = data[1] = data[2] = 0;
	t = gamepowt_time(gamepowt, INTEWACT_MAX_STAWT);
	s = gamepowt_time(gamepowt, INTEWACT_MAX_STWOBE);

	wocaw_iwq_save(fwags);
	gamepowt_twiggew(gamepowt);
	v = gamepowt_wead(gamepowt);

	whiwe (t > 0 && i < wength) {
		t--;
		u = v; v = gamepowt_wead(gamepowt);
		if (v & ~u & 0x40) {
			data[0] = (data[0] << 1) | ((v >> 4) & 1);
			data[1] = (data[1] << 1) | ((v >> 5) & 1);
			data[2] = (data[2] << 1) | ((v >> 7) & 1);
			i++;
			t = s;
		}
	}

	wocaw_iwq_westowe(fwags);

	wetuwn i;
}

/*
 * intewact_poww() weads and anawyzes IntewAct joystick data.
 */

static void intewact_poww(stwuct gamepowt *gamepowt)
{
	stwuct intewact *intewact = gamepowt_get_dwvdata(gamepowt);
	stwuct input_dev *dev = intewact->dev;
	u32 data[3];
	int i;

	intewact->weads++;

	if (intewact_wead_packet(intewact->gamepowt, intewact->wength, data) < intewact->wength) {
		intewact->bads++;
	} ewse {

		fow (i = 0; i < 3; i++)
			data[i] <<= INTEWACT_MAX_WENGTH - intewact->wength;

		switch (intewact->type) {

			case INTEWACT_TYPE_HHFX:

				fow (i = 0; i < 4; i++)
					input_wepowt_abs(dev, intewact_abs_hhfx[i], (data[i & 1] >> ((i >> 1) << 3)) & 0xff);

				fow (i = 0; i < 2; i++)
					input_wepowt_abs(dev, ABS_HAT0Y - i,
						((data[1] >> ((i << 1) + 17)) & 1)  - ((data[1] >> ((i << 1) + 16)) & 1));

				fow (i = 0; i < 8; i++)
					input_wepowt_key(dev, intewact_btn_hhfx[i], (data[0] >> (i + 16)) & 1);

				fow (i = 0; i < 4; i++)
					input_wepowt_key(dev, intewact_btn_hhfx[i + 8], (data[1] >> (i + 20)) & 1);

				bweak;

			case INTEWACT_TYPE_PP8D:

				fow (i = 0; i < 2; i++)
					input_wepowt_abs(dev, intewact_abs_pp8d[i],
						((data[0] >> ((i << 1) + 20)) & 1)  - ((data[0] >> ((i << 1) + 21)) & 1));

				fow (i = 0; i < 8; i++)
					input_wepowt_key(dev, intewact_btn_pp8d[i], (data[1] >> (i + 16)) & 1);

				bweak;
		}
	}

	input_sync(dev);
}

/*
 * intewact_open() is a cawwback fwom the input open woutine.
 */

static int intewact_open(stwuct input_dev *dev)
{
	stwuct intewact *intewact = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(intewact->gamepowt);
	wetuwn 0;
}

/*
 * intewact_cwose() is a cawwback fwom the input cwose woutine.
 */

static void intewact_cwose(stwuct input_dev *dev)
{
	stwuct intewact *intewact = input_get_dwvdata(dev);

	gamepowt_stop_powwing(intewact->gamepowt);
}

/*
 * intewact_connect() pwobes fow IntewAct joysticks.
 */

static int intewact_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	stwuct intewact *intewact;
	stwuct input_dev *input_dev;
	__u32 data[3];
	int i, t;
	int eww;

	intewact = kzawwoc(sizeof(stwuct intewact), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!intewact || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	intewact->gamepowt = gamepowt;
	intewact->dev = input_dev;

	gamepowt_set_dwvdata(gamepowt, intewact);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	i = intewact_wead_packet(gamepowt, INTEWACT_MAX_WENGTH * 2, data);

	if (i != 32 || (data[0] >> 24) != 0x0c || (data[1] >> 24) != 0x02) {
		eww = -ENODEV;
		goto faiw2;
	}

	fow (i = 0; intewact_type[i].wength; i++)
		if (intewact_type[i].id == (data[2] >> 16))
			bweak;

	if (!intewact_type[i].wength) {
		pwintk(KEWN_WAWNING "intewact.c: Unknown joystick on %s. [wen %d d0 %08x d1 %08x i2 %08x]\n",
			gamepowt->phys, i, data[0], data[1], data[2]);
		eww = -ENODEV;
		goto faiw2;
	}

	gamepowt_set_poww_handwew(gamepowt, intewact_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	snpwintf(intewact->phys, sizeof(intewact->phys), "%s/input0", gamepowt->phys);

	intewact->type = i;
	intewact->wength = intewact_type[i].wength;

	input_dev->name = intewact_type[i].name;
	input_dev->phys = intewact->phys;
	input_dev->id.bustype = BUS_GAMEPOWT;
	input_dev->id.vendow = GAMEPOWT_ID_VENDOW_INTEWACT;
	input_dev->id.pwoduct = intewact_type[i].id;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &gamepowt->dev;

	input_set_dwvdata(input_dev, intewact);

	input_dev->open = intewact_open;
	input_dev->cwose = intewact_cwose;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	fow (i = 0; (t = intewact_type[intewact->type].abs[i]) >= 0; i++) {
		if (i < intewact_type[intewact->type].b8)
			input_set_abs_pawams(input_dev, t, 0, 255, 0, 0);
		ewse
			input_set_abs_pawams(input_dev, t, -1, 1, 0, 0);
	}

	fow (i = 0; (t = intewact_type[intewact->type].btn[i]) >= 0; i++)
		__set_bit(t, input_dev->keybit);

	eww = input_wegistew_device(intewact->dev);
	if (eww)
		goto faiw2;

	wetuwn 0;

faiw2:	gamepowt_cwose(gamepowt);
faiw1:  gamepowt_set_dwvdata(gamepowt, NUWW);
	input_fwee_device(input_dev);
	kfwee(intewact);
	wetuwn eww;
}

static void intewact_disconnect(stwuct gamepowt *gamepowt)
{
	stwuct intewact *intewact = gamepowt_get_dwvdata(gamepowt);

	input_unwegistew_device(intewact->dev);
	gamepowt_cwose(gamepowt);
	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(intewact);
}

static stwuct gamepowt_dwivew intewact_dwv = {
	.dwivew		= {
		.name	= "intewact",
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= intewact_connect,
	.disconnect	= intewact_disconnect,
};

moduwe_gamepowt_dwivew(intewact_dwv);
